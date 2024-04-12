//==============================================================================
//==============================================================================
// Application
//==============================================================================
//==============================================================================
//
// Directive "noinspection" must exist in initial comment block
//
// noinspection zzz,JSUnusedLocalSymbols,Annotator

// Code

//==============================================================================
//==============================================================================
// Notes
//==============================================================================
//==============================================================================

//==============================================================================
// Documentation
//==============================================================================

// MDN Web Docs
// https://developer.mozilla.org

// React
// https://react.dev/

// Next.js
// https://nextjs.org/

// SWR
// https://swr.vercel.app/

// NextJS API Routes
// https://nextjs.org/docs/pages/building-your-application/routing/api-routes

//==============================================================================
//==============================================================================
// Import
//==============================================================================
//==============================================================================

//==============================================================================
// Libraries
//==============================================================================

//import path from 'path';
//import { promises as fs } from 'fs';
import _ from 'lodash';
import useSWR from 'swr';

//==============================================================================
// Frameworks
//==============================================================================

import type { MouseEvent } from 'react';
import {useState} from 'react';
//import {useReducer} from 'react';
//import {createContext} from 'react';
//import {useContext} from 'react';
//import {Dispatch} from 'react';
//import {ReactNode} from 'react';

//import type {NextApiRequest} from 'next';
//import type {NextApiResponse} from 'next';

import Head from 'next/head';
import Image from 'next/image';
//import Link from 'next/link';

//==============================================================================
// Interfaces and types
//==============================================================================

//import type {CustomObject} from '@/interfaces';
import type {Item} from '@/interfaces/data';
import type {Items} from '@/interfaces/data';
import type {Auth} from '@/interfaces/auth';

//==============================================================================
// Data components
//==============================================================================

//import { CustomContext } from '@/context/customcontext';
//import { useMainData, useDispatchMainData } from '@/context/maindatacontext'

//==============================================================================
// Display components
//==============================================================================

//import CustomComponent from '@/components/customcomponent';
//import Bar from '@/components/bar';

import Headerbar from '@/components/headerbar';
import Navbar from '@/components/navbar';
import Footerbar from '@/components/footerbar';
import Debugbar from '@/components/debugbar';

import ItemComponent from '@/components/Item'
import ItemCartComponent from '@/components/ItemCart'

//==============================================================================
//==============================================================================
// Types
//==============================================================================
//==============================================================================

//type CustomObject = {
//  id: number;
//  name: string;
//};

//type CustomObjectColl = CustomObject[];

//==============================================================================
//==============================================================================
// Functions
//==============================================================================
//==============================================================================

// function ff() {}

const fetcher = (url: string) => fetch(url).then((res) => res.json())

//==============================================================================
//==============================================================================
// Data
//==============================================================================
//==============================================================================

//let id: number = 0;

//==============================================================================
//==============================================================================
// Code
//==============================================================================
//==============================================================================

//function ff() {}

//==============================================================================
// Main component
//==============================================================================
export default function ItemsCategory() {

  //============================================================================

  const { data : nature_data, error: nature_error, isLoading: nature_isLoading } = useSWR<Item[]>('/api/category/nature', fetcher)
    const { data : transportation_data, error: transportation_error, isLoading: transportation_isLoading} = useSWR<Item[]>('/api/category/transportation', fetcher)
    const { data : electronic_data, error: electronic_error, isLoading: electronic_isLoading} = useSWR<Item[]>('/api/category/electronic', fetcher)
    const { data : geographic_data, error: geographic_error, isLoading: geographic_isLoading} = useSWR<Item[]>('/api/category/geographic', fetcher)

  //const { dataNature, errorNature, isLoadingNature } = useSWRnature<Item[]>('/api/category/nature', fetcher)
  //const { dataElectronic, errorElectronic, isLoadingElectronic } = useSWRelectronic<Item[]>('/api/category/electronic', fetcher)
  //console.log({"data": data});

  //const mainData = useMainData()
  //const dispatchMainData = useDispatchMainData()

  //============================================================================

  return (
    <main className="flex flex-col zzz-items-center zzz-justify-between p-24">

      <Headerbar/>
      <Navbar/>

      <div className="py-1 px-1 mb-1 bg-gray-100 text-center text-lg">
        <p>Item Categories</p>
      </div>

      <div className="py-1 px-1 mb-1 bg-gray-100 text-center">
        <p>List of available items grouped by category</p>
      </div>

        <div className="py-1 px-1 mb-1 bg-gray-100 text-center">
            <p>Nature</p>
            <p>(All available items in this category)</p>
            {/*<p>(TODO: Show all item information with graphics for this category - and remove this message)</p>*/}
            <div className="flex flex-col zzz-items-center zzz-justify-between grid grid-cols-3 gap-1">
                {
                    (() => {
                        if (nature_error) return <div>Error loading</div>
                        if (nature_isLoading) return <div>Loading</div>
                        if (!nature_data) return <div>Data error</div>
                        return nature_data?.map((i) => (<ItemCartComponent key={i.name} item={i}/>))
                    })()
                }
            </div>
        </div>

        <div className="py-1 px-1 mb-1 bg-gray-100 text-center">
            <p>Transportation Devices</p>
            <p>(All available items in this category)</p>
            {/*<p>(TODO: Show all item information with graphics for this category -*/}
            {/*    and remove this message)</p>*/}
            <div className="flex flex-col zzz-items-center zzz-justify-between grid grid-cols-3 gap-1">
                {
                    (() => {
                        if (transportation_error) return <div>Error loading</div>
                        if (transportation_isLoading) return <div>Loading</div>
                        if (!transportation_data) return <div>Data error</div>
                        return transportation_data?.map((i) => (<ItemCartComponent key={i.name} item={i}/>))
                    })()
                }
            </div>
        </div>

        <div className="py-1 px-1 mb-1 bg-gray-100 text-center">
            <p>Electronic Items</p>
            <p>(All available items in this category)</p>
            {/*<p>(TODO: Show all item information with graphics for this category -*/}
            {/*    and remove this message)</p>*/}
            <div className="flex flex-col zzz-items-center zzz-justify-between grid grid-cols-3 gap-1">
                {
                    (() => {
                        if (electronic_error) return <div>Error loading</div>
                        if (electronic_isLoading) return <div>Loading</div>
                        if (!electronic_data) return <div>Data error</div>
                        return electronic_data?.map((i) => (<ItemCartComponent key={i.name} item={i}/>))
                    })()
                }
            </div>
        </div>

        <div className="py-1 px-1 zzz-mb-1 bg-gray-100 text-center">
            <p>Geographic</p>
            <p>(All available items in this category)</p>
            {/*<p>(TODO: Show all item information with graphics for this category -*/}
            {/*    and remove this message)</p>*/}
            <div className="flex flex-col zzz-items-center zzz-justify-between grid grid-cols-3 gap-1">
                {
                    (() => {
                        if (geographic_error) return <div>Error loading</div>
                        if (geographic_isLoading) return <div>Loading</div>
                        if (!geographic_data) return <div>Data error</div>
                        return geographic_data?.map((i) => (<ItemCartComponent key={i.name} item={i}/>))
                    })()
                }
            </div>
        </div>
        <Footerbar/>

        <Debugbar/>

    </main>
  )
}

//==============================================================================
//==============================================================================
// Export
//==============================================================================
//==============================================================================

//export default main;

//==============================================================================
//==============================================================================
// Other
//==============================================================================
//==============================================================================
